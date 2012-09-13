#ifdef ps_hpux
/*D***********************************************************
 * modul:     AUDIO functions for HP-UX                 
 *
 * copyright: Yafra.org, Switzerland     
 *            Hewlett-Packard Co.,  All Rights Reserved.
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/aud_hp.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#ifndef __C2MAN__ 
#include <Alib.h>
#include <CUlib.h>
#include "aud_hp.h"
#endif

#include <psmume.h>


/************************************************************
 * play an audio WAV file on a Aserver
 *
 * audio player for HP workstations
 *
 * returns     int as an error code
 * 
 * library:    audio
 *
 * include:    psaudio.h
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * HP-UX port  (c) by Hewlett-Packard Co.,  All Rights Reserved.
 *
 * author:     Administrator
 **************************************************************/
int HPaudio_play(char *filename, char *server, int stereoflag, int loop)
{
	extern long myHandler();
	
	long            status;
	SSPlayParams    streamParams;
	AGainEntry      gainEntry[4];
	ATransID        xid;
	char            afile[80], c;
	int             arg;
	AEvent          event;
	AFileFormat     switchFormat;
	Audio           *audio;
	int             n, switchCode, loopCount;
	char            *pSpeaker;
	AudioAttrMask   AttribsMask, PlayAttribsMask, ignoredMask;
	AudioAttributes Attribs, PlayAttribs;
	AErrorHandler   prevHandler;  /* pointer to previous handler */
	SStream	  audioStream;
	int		  fd, len, inLen, len_written;
	FILE            *pfile;
	int		  streamSocket;
	char            *inBuf, *bufBase, *buf;
	SunHeader       auFileHeader;
	Bool            filenameFound, audioPaused;
	int             useIntSpeaker;
	long            seekOffset, data_length, bytes_written,bytes_read, pauseCount;
	AByteOrder      byte_order, play_byte_order;
	AConvertParams  *convert_params;
	
	/*
   * process command line switches
   */
	
	loopCount = 1;
	streamParams.priority = APriorityNormal;          /* normal priority */
	filenameFound = False;
	switchFormat = AFFUnknown;
	AttribsMask = 0;
	PlayAttribsMask = 0;
	seekOffset = 0;
	
	
	streamParams.priority = APriorityNormal;          /* normal priority */
	
	if (stereoflag == 1)
	{
		Attribs.attr.sampled_attr.channels = 2;
		AttribsMask = (AttribsMask | ASChannelsMask);
	}
	
	strcpy(afile, filename);
	filenameFound = True;
	
	
	/* replace default error handler */
	prevHandler = ASetErrorHandler(myHandler);
	
	/*
   *  open audio connection
   */
	audio = AOpenAudio(server, NULL );
	
	/*
   * open the audio file (if any)
   */
	
	if ( filenameFound ) {
		fd = open( afile, O_RDONLY );
		if( fd < 0 ) {
			perror( "file open failed" );
			return(1);
		}
		pfile =fdopen( fd, "r");
	} 
	else {
		/* no filename specified, read audio stream from stdin */
		fd = fileno( stdin );
		pfile =NULL;
	}
	
	/*
   *  Determine attributes of source
   */
	
	AChooseSourceAttributes(audio, afile, pfile, switchFormat, AttribsMask, &Attribs, &seekOffset,
                           &data_length, &byte_order, NULL );
	
	/*
   * Select attributes for playback
   */
	
	AChoosePlayAttributes (audio, &Attribs, PlayAttribsMask, &PlayAttribs, &play_byte_order, NULL );
	
	/*
   * setup the playback parameters
   */
	pSpeaker = getenv( "SPEAKER" );         /* get user speaker preference */
	if ( pSpeaker ) {
		useIntSpeaker = ( (*pSpeaker == 'i') || (*pSpeaker == 'I') );
	} else {
		/* SPEAKER environment variable not found - use internal speaker */  
		useIntSpeaker = 1;
	}
	switch(PlayAttribs.attr.sampled_attr.channels ) {
		case 1:
			gainEntry[0].u.o.out_ch = AOCTMono;
			gainEntry[0].gain = AUnityGain;
			gainEntry[0].u.o.out_dst = (useIntSpeaker) ? AODTMonoIntSpeaker : AODTMonoJack;
			break;
		case 2:
		default:    /* assume no more than 2 channels */
			gainEntry[0].u.o.out_ch = AOCTLeft;
			gainEntry[0].gain = AUnityGain;
			gainEntry[0].u.o.out_dst = (useIntSpeaker) ? AODTLeftIntSpeaker : AODTLeftJack;
			gainEntry[1].u.o.out_ch = AOCTRight;
			gainEntry[1].gain = AUnityGain;
			gainEntry[1].u.o.out_dst = (useIntSpeaker) ? AODTRightIntSpeaker : AODTRightJack;
			break;
	}
	streamParams.gain_matrix.type = AGMTOutput;       /* gain matrix */
	streamParams.gain_matrix.num_entries = PlayAttribs.attr.sampled_attr.channels;
	streamParams.gain_matrix.gain_entries = gainEntry;
	streamParams.play_volume = AUnityGain;            /* play volume */
	streamParams.priority = APriorityNormal;          /* normal priority */
	streamParams.event_mask = 0;                      /* don't solicit any events */
	
	/*
   * create an audio stream
   */
	xid = APlaySStream( audio, ~0, &PlayAttribs, &streamParams,
							 &audioStream, NULL );
	/*
	* create a stream socket
	*/
	streamSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( streamSocket < 0 ) {
		perror( "Socket creation failed" );
		return(1);
	}
	
	/*
   * connect the stream socket to the audio stream port
   */
	status = connect( streamSocket, (struct sockaddr *)&audioStream.tcp_sockaddr,
						  sizeof(struct sockaddr_in) );
	if( status < 0 ) {
		perror( "Connect failed" );
		return(1);
	}
	
	/*
   * prevent attempting to loop if audio data source is stdin
   */
	if ( !filenameFound ) {
		loopCount = 1;
	}
	
	/*
   * allocate a buffer for the converted data
   */
	bufBase = malloc( audio->block_size );
	
	/*
   * calculate the required buffer size for the data prior to conversion
   */
	inLen = ACalculateLength (audio, audio->block_size, &PlayAttribs, &Attribs, NULL); 
   
	/*
   * allocate a buffer for the pre-converted data
   */
	inBuf = malloc(inLen );
	
	/*
   * start stream paused so we can transfer enough data (3 seconds worth) before
   *  playing starts to prevent stream from running out 
   */
	APauseAudio( audio, xid, NULL, NULL );
	pauseCount = 3 * PlayAttribs.attr.sampled_attr.channels
		* PlayAttribs.attr.sampled_attr.sampling_rate
		* (PlayAttribs.attr.sampled_attr.bits_per_sample >> 3);
	audioPaused = True;
	
	/*
   * prepare for conversion. Must remember to free convert_params by calling AEndConversion
   */
	convert_params = ASetupConversion (audio, &Attribs, &byte_order, &PlayAttribs, &play_byte_order, NULL );
	
	/*
   * Loop # of times specified by user
   */
	while ( loopCount ) {
		
		/*
		* seek to beginning of audio data
		*/
		lseek( fd, seekOffset, SEEK_SET );
		
		while(( len = read( fd, inBuf, inLen )) > 0 ) {
			/*
			* read a buffer-full of data from the file & convert it
			*/
			AConvertBuffer(audio, convert_params, inBuf, len, bufBase, audio->block_size, 
								&bytes_read, &bytes_written, NULL) ; 
			
			len = bytes_written;
			buf = bufBase;
			/*
			* write the converted data to the stream socket
			*/
			while( len ) {
				/*
				* write converted data to stream socket until we have emptied buffer
				*/
				if(( len_written = write( streamSocket, buf, len )) < 0 ) {
					perror( "write failed" );
					return(1);
				}
				buf += len_written;
				len -= len_written;
				if ( audioPaused ) {
					pauseCount -= len_written;
					if ( (len_written == 0) || ( pauseCount <= 0) ) {
						AResumeAudio( audio, xid, NULL, NULL );
						audioPaused = False;
					}
				}
			}
		}
		loopCount--;
	}
	if ( audioPaused ) {
		AResumeAudio( audio, xid, NULL, NULL );
	}
	
	/* free the convert_params structure and flush out the conversion pipeline */
	AEndConversion(audio, convert_params, bufBase, audio->block_size, &bytes_written, NULL) ;   
	
	len = bytes_written;
	buf = bufBase;
	/*
   * write the converted data to the stream socket
	*/
	while( len ) {
      /*
		* write converted data to stream socket until we have emptied buffer
      */
      if(( len_written = write( streamSocket, buf, len )) < 0 ) {
			perror( "write failed" );
			return(1);
      }
      buf += len_written;
      len -= len_written;
	}

	free(bufBase);
	free(inBuf);

	if ( filenameFound ) {
		close( fd );
	}
	
	close( streamSocket );
	/*
   * set close mode to prevent playback from stopping 
   *  when we close audio connection
   */
	ASetCloseDownMode( audio, AKeepTransactions, NULL );
	
	/*
   *  That's all, folks!
   */
	ACloseAudio( audio, NULL );
	return(0);
}

#ifndef __C2MAN__

/*SF**********************************************************
 * function:  error handler for splayer
 **************************************************************/
long myHandler(Audio  *audio, AErrorEvent  *err_event)
{
	printAudioError( audio, "Oh Mercy", err_event->error_code ); 

	exit(1);
}

#endif

#define TIME_SWITCH      0
#define PAUSE_SWITCH     1
#define GRAB_SWITCH      2
#define SRATE_SWITCH     3
#define STEREO_SWITCH    4
#define LINEIN_SWITCH    5
#define CONNECT_SWITCH   6
#define DATA_SWITCH      7

/*
 * getFreeSocketAddress - get free socket address for accepting connections
 *  returns 0 for success
 */
int getFreeSocketAddress(struct sockaddr_in *streamSocketAddr, int socketFD)
{
	/* fill in requestSocket name */
	bzero ((char *)streamSocketAddr, sizeof(struct sockaddr_in));
	streamSocketAddr->sin_family = AF_INET;
	streamSocketAddr->sin_addr.s_addr = htonl(INADDR_ANY);
	/*
	* try binding to different ports until we find one that works
	*/
	streamSocketAddr->sin_port = IPPORT_USERRESERVED;
	while ( bind( socketFD, (struct sockaddr *) streamSocketAddr, 
					 sizeof( struct sockaddr_in ) ) ) {
		/* try 10000 times to get a port address assigned to aserver */
		if ( (streamSocketAddr->sin_port - IPPORT_USERRESERVED) > 10000 ) {
			/*
			* report failure getting a free socket address
			*/
			return 1;
		}
		streamSocketAddr->sin_port++;
	}
	
	/*
	* we got a socket address assigned
	*/
	return 0;
}


int HPaudio_record(char *filename, char *server, int stereoflag, int loop)
{
	extern long myHandler();
	long            status;
	SSRecordParams  streamParams;
	AGainEntry      gainEntry[4];
	ATransID        xid;
	char            afile[80], c;
	int             arg;
	AEvent          event;
	AFileFormat     fileFormat, extnFormat, tempFormat;
	Audio           *audio;
	AudioAttrMask   AttribsMask;
	AudioAttributes Attribs, recordAttribs;
	AErrorHandler   prevHandler;  /* pointer to previous handler */
	SStream	  audioStream;
	int		  fd, len, outLen, numWritten;
	int		  streamSocket, streamConnectFD;
	char	          *buf, *outBuf, *bufBase;
	long            seconds;
	struct sockaddr clientSAddr;        /* client socket internet address */
	int             clientSAddrLen;     /* length of client address */
	fd_set          selectedFDs;        /* file descriptor for select */
	fd_set          readyFDs;           /* FDs ready for IO from select */
	struct timeval  timeout;            /* timeout for select */
	int             maxFD, stdinFD;
	unsigned long   numLeft;
	int             numReady;
	Bool            filenameFound;
	Bool            doGrab;
	Bool            doPause;
	unsigned long   *s_rates;
	unsigned long   extnRate;
	Bool            useLineIn;
	int             n, switchCode, i;
	Bool            useConnect;
	AByteOrder      byte_order, record_byte_order;
	ADataFormat     *formats;
	AConvertParams  *convert_params;
	long            bytes_read, bytes_written;
	
	/* replace default error handler */
	prevHandler = ASetErrorHandler(myHandler);
	
	/*
   *  open audio connection
   */
	server[0] = '\0';
	audio = AOpenAudio( server, NULL);
	
	/*
   * process command line switches
   */
	AttribsMask = 0;
	fileFormat = AFFUnknown;
	seconds = 0;
	filenameFound = False;
	doGrab = False;
	doPause = False;
	useLineIn = False;
	useConnect = False;
	
	
	/* user specified a duration */
	seconds = 1;
	
	/* user specified pause first */
	doPause = True;
	
	/* user specified grab server before recording */
	doGrab = True;
	
	/* user specified sampling rate for target file */
	Attribs.attr.sampled_attr.sampling_rate = 1;
	AttribsMask = (AttribsMask | ASSamplingRateMask);
	
	/* user specified stereo */
	Attribs.attr.sampled_attr.channels = 2;
	AttribsMask = (AttribsMask | ASChannelsMask);
	
	/* user specified using line input instead of mike */
	useLineIn = True;
	
	/* user specified using AConnectRecordStream instead of ARecordStream */
	useConnect = True;
	
	/* see if it is a valid data format */
	Attribs.attr.sampled_attr.data_format = findDataFormat(filename);
	if (Attribs.attr.sampled_attr.data_format == ADFUnknown ) {
		fprintf( stderr, "Bad Data Format: %s\n", filename );
	}
	else {
		AttribsMask = (AttribsMask | ASDataFormatMask);
	}
	
	strcpy(afile, filename); 
	filenameFound = True;
	
	/*
   * check filename for file format or sample rate specifiers
   */
	if ( filenameFound ) {
		n = name2format( afile, &extnFormat, &extnRate );
		
		/* do not use file extension format/sample rate if already specified */
		if ( (fileFormat == AFFUnknown ) && (n > 0) ) {
			fileFormat = extnFormat;
		}
		if ( ~(AttribsMask & ASSamplingRateMask) && (n > 1)) {
			Attribs.attr.sampled_attr.sampling_rate = extnRate;
			AttribsMask = (AttribsMask | ASSamplingRateMask);
		}
	}
	else {
		/* no filename found. Must be writing to stdout */
		switch (fileFormat) {
			case AFFRiffWave:
			case AFFSun:
				fprintf( stderr, "Warning: The file header will not be written to stdout\n" );
				break;
		}
	}
	/*
   * Choose attributes for the target file
   */       
	AChooseAFileAttributes (audio, aBestAudioAttributes(audio), fileFormat, AttribsMask, 
									&Attribs, &byte_order, NULL );
	
	/*
   * Choose record attributes
   */       
	recordAttribs = *aBestAudioAttributes(audio);   /* set to the default. (individaul attributes may be overwritten) */
	record_byte_order = aSoundByteOrder(audio);
	
	if (recordAttribs.attr.sampled_attr.data_format !=Attribs.attr.sampled_attr.data_format) {
		n = aNumDataFormats(audio); 
		formats = aDataFormats(audio);
		for (i=0; i < n; i++) {
			if (Attribs.attr.sampled_attr.data_format == formats[i] ) {
				recordAttribs.attr.sampled_attr.data_format = Attribs.attr.sampled_attr.data_format;
				recordAttribs.attr.sampled_attr.bits_per_sample = Attribs.attr.sampled_attr.bits_per_sample;
				break;    
			} 
		}
	}
	if (recordAttribs.attr.sampled_attr.sampling_rate !=Attribs.attr.sampled_attr.sampling_rate) {
		n = aNumSamplingRates(audio); 
		s_rates = aSamplingRates(audio);
		for (i=0; i < n; i++) {
			if (Attribs.attr.sampled_attr.sampling_rate == s_rates[i] ) {
				recordAttribs.attr.sampled_attr.sampling_rate = Attribs.attr.sampled_attr.sampling_rate;
				break;    
			} 
		}
	}
	if (recordAttribs.attr.sampled_attr.channels !=Attribs.attr.sampled_attr.channels) {
		if ( (Attribs.attr.sampled_attr.channels == 2) && (aInputChannels(audio) & ALeftOutputChMask)) {
			recordAttribs.attr.sampled_attr.channels = Attribs.attr.sampled_attr.channels;
			recordAttribs.attr.sampled_attr.interleave = Attribs.attr.sampled_attr.interleave;
		}
		else if ( (Attribs.attr.sampled_attr.channels == 1) && (aInputChannels(audio) & AMonoOutputChMask)) {
			recordAttribs.attr.sampled_attr.channels = Attribs.attr.sampled_attr.channels;
		}   
	}
	
	/*
   * setup the record parameters
   */
	switch(recordAttribs.attr.sampled_attr.channels) {
		case 1:
			gainEntry[0].u.i.in_ch = AICTMono;
			gainEntry[0].gain = AUnityGain;
			gainEntry[0].u.i.in_src = (useLineIn) ? AISTMonoAuxiliary : AISTMonoMicrophone;
			break;
		case 2:
		default:    /* assume no more than 2 channels */
			gainEntry[0].u.i.in_ch = AICTLeft;
			gainEntry[0].gain = AUnityGain;
			gainEntry[0].u.i.in_src = (useLineIn) ? AISTLeftAuxiliary : AISTLeftMicrophone;
			gainEntry[1].u.i.in_ch = AICTRight;
			gainEntry[1].gain = AUnityGain;
			gainEntry[1].u.i.in_src = (useLineIn) ? AISTRightAuxiliary : AISTRightMicrophone;
			break;
	}
	streamParams.gain_matrix.type = AGMTInput;
	streamParams.gain_matrix.num_entries = recordAttribs.attr.sampled_attr.channels;
	streamParams.gain_matrix.gain_entries = gainEntry;
	streamParams.record_gain = AUnityGain;            /* record gain */
	streamParams.event_mask = 0;                      /* don't solicit any events */
	
	/*
   * grab the server if user specified to
   */
	if ( doGrab ) {
		if ( AGrabServer( audio, NULL ) == False ) {
			fprintf( stderr, "Server grab failed\n" );
			doGrab = False;
		}
	}
	
	/*
   * create a stream socket
   */
	streamSocket = socket( AF_INET, SOCK_STREAM, 0 );
	if( streamSocket < 0 ) {
		perror( "Socket creation failed" );
		exit(1);
	}
	
	/*
   * create or connect to an audio stream
   */
	if ( useConnect ) {
		
		/*
		* we will use the socket just created only to make connection -
		*  the streamSocket for audio IO will be returned by "accept"
		*/
		streamConnectFD = streamSocket;
		
		/*
		* fill in audioStream structure with socket address & stream attributes
		*/
		if ( getFreeSocketAddress( &(audioStream.tcp_sockaddr), streamConnectFD ) ) {
			perror( "Failed to bind socket address" );
			exit(1);
		}
		if ( listen( streamConnectFD, 1 ) < 0 ) {
			perror( "Failed in listen" );
		}
		audioStream.audio_attr = recordAttribs;
		audioStream.max_block_size = audio->block_size;
		
		xid = AConnectRecordSStream( audio, &audioStream, &streamParams, NULL );
	} else {
		
		xid = ARecordSStream( audio, ~0, &recordAttribs, &streamParams,
									&audioStream, NULL );
	}
	
	/*
   * wait for user to hit key to begin recording
   */
	if ( doPause ) {
		fprintf( stderr, "Hit RETURN to start recording\n" );
		c = getchar();
	}
	
	/*
   * connect the stream socket to the audio stream port
   */
	if ( useConnect ) {
		streamSocket = accept( streamConnectFD, &clientSAddr, &clientSAddrLen );
		if ( streamSocket < 0 ) {
			perror( "Failed in accept" );
		}
	} else {
		status = connect( streamSocket, (struct sockaddr *)&audioStream.tcp_sockaddr,
							  sizeof(struct sockaddr_in) );
		if( status < 0 ) {
			perror( "Connect failed" );
			exit(1);
		}
	}
	
	/*
   * open the audio file (if any) & write the file header (if needed)
   */
	
	if ( filenameFound ) {
		AWriteAFileHeader (audio, afile, fileFormat, &Attribs, NULL);
		fd = open( afile, O_WRONLY | O_CREAT | O_APPEND, 0666 );
		if( fd < 0 ) {
			perror( "file open failed" );
			exit(1);
		}
	} else {
		/* no filename specified, send audio stream to stdout */
		fd = fileno( stdout );
	}
	
	/*
   * allocate a buffer to receive recorded data
   */
	
	bufBase = malloc( audio->block_size );
	
	/*
   * calculate the size of 1 buffer of data after conversion
   */
	outLen = ACalculateLength (audio, audio->block_size, &recordAttribs, &Attribs, NULL); 
   
	/*
   * allocate a buffer for the converted data
   */
	outBuf = malloc(outLen );
   
	/*
   * prepare for conversion. (Must remember to free convert_params by calling AEndConversion)
   */
	convert_params = ASetupConversion (audio, &recordAttribs, &record_byte_order, &Attribs, &byte_order, NULL );
	
	/*
   *  read data until either the specified duration is reached or
   *   the user hits a console key
   */
	
	fprintf( stderr, "Hit RETURN to stop recording\n" );
	
	if ( seconds ) {
		numLeft = seconds 
			* recordAttribs.attr.sampled_attr.sampling_rate
			* (recordAttribs.attr.sampled_attr.bits_per_sample / 8) 
			* recordAttribs.attr.sampled_attr.channels;
	} else {
		numLeft = ~0;
	}
	stdinFD = fileno( stdin );
	maxFD = ( streamSocket > stdinFD ) ? streamSocket : stdinFD ;
	FD_ZERO( &readyFDs );
	FD_ZERO( &selectedFDs );
	FD_SET( stdinFD, &selectedFDs );
	FD_SET( streamSocket, &selectedFDs );
	while ( numLeft ) {
		readyFDs = selectedFDs;
		numReady = select( maxFD + 1, (int *) &readyFDs, (int *) NULL,
								(int *) NULL, (struct timeval *) 0 );
		if ( numReady < 0 ) {
			perror( "select failed" );
			exit(1);
		}
		
		if ( FD_ISSET( streamSocket, &readyFDs ) ) {
			/* record stream has data available */
			len = read( streamSocket, bufBase, audio->block_size );
			if ( len > numLeft ) len = numLeft;
			if ( len > 0 ) {
				/* convert to target format */
				AConvertBuffer(audio, convert_params, bufBase,len, outBuf, outLen, 
									&bytes_read, &bytes_written, NULL) ; 
				
				numLeft -= bytes_read;
				len = bytes_written;
				buf = outBuf;
				while( len ) {
					if (( numWritten = write( fd, buf, len )) < 0 ) {
						/* error on write - force end of recording */
						perror( "write failed" );
						numLeft = 0;
						len = 0;
					} else {
						buf += numWritten;
						len -= numWritten;
					}
				}
			} else {
				/* error on read (or stop) from audio stream - force end of recording */
				numLeft = 0;
			}
		}
		
		if ( FD_ISSET( stdinFD, &readyFDs ) ) {
			/* user hit a key, force end of recording */
			FD_CLR( stdinFD, &selectedFDs );
			AStopAudio( audio, xid, ASMThisTrans, (ATransStatus *) NULL, NULL );
		}
		
	}   /* while numLeft */
	/* free the convert_params structure */
	AEndConversion(audio, convert_params, outBuf, outLen, &bytes_written, NULL) ;   
	
	close( streamSocket );
	if ( filenameFound ) {
		close( fd );
		/* update the file header (if any) with the new data length */
		AUpdateDataLength( audio, afile, fileFormat, NULL);
	}
	
	
	/*
   * release the server if grabbed
   */
	if ( doGrab ) {
		AUngrabServer( audio, NULL );
	}
	
	/*
   *  That's all, folks!
   */
	free(bufBase);
	free(outBuf);
	ACloseAudio( audio, &status );
	exit(0);
}

#endif
