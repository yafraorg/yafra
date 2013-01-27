<?php include('ahead.php');?>  

    <div class="navbar navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container">
          <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </a>
          <a class="brand" href="/"><img src="/img/org-yafra2.jpg"></a>
          <div class="nav-collapse collapse">
            <ul class="nav nav-pills pull-right">
              <li class="active"><a href="/">Home</a></li>
              <li><a href="/project.php">Projects</a></li>
              <li><a href="https://github.com/yafraorg/yafra/wiki">Wiki</a></li>
            </ul>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>

    <div class="container">


      <div class="row">
        <div class="span12">
            <div class="bs-docs-example">
              <div id="myCarousel" class="carousel slide">
                <div class="carousel-inner">
                  <div class="item active">
                    <img src="/img/A1.jpg" alt="">
                    <div class="carousel-caption">
                      <h4>Java multitier applications</h4>
                      <p>Take the code basis in order to build your own java multitier application using J2EE technologies.</p>
                    </div>
                  </div>
                  <div class="item">
                    <img src="/img/A3.jpg" alt="">
                    <div class="carousel-caption">
                      <h4>Integrate legacy systems</h4>
                      <p>Examples on how to integrate legacy ANSI C code into a modern information technology world.</p>
                    </div>
                  </div>
                  <div class="item">
                    <img src="/img/A2.jpg" alt="">
                    <div class="carousel-caption">
                      <h4>Object relational database modelling</h4>
                      <p>Use your database with objects instead of traditional queries.</p>
                    </div>
                  </div>
                </div>
                <a class="left carousel-control" href="#myCarousel" data-slide="prev">&lsaquo;</a>
                <a class="right carousel-control" href="#myCarousel" data-slide="next">&rsaquo;</a>
              </div>
            </div>
        </div>
      </div>

      <div class="row">
        <div class="span12">
        <br />
        <br />
        <br />
        </div>
      </div>


          <div class="row">
            <div class="span4">
              <h2>J2EE with Apache Software</h2>
              <p>This sample uses the Apache Cayenne ORM, Apache TOMEE/Tomcat or Jetty as server and Apache Wicket, OpenEJB, Apache CXF and Google Web Toolkit as web frameworks. It shows how you can utilise Apache Cayenne running within the same virtual machine and on different machines. This sample has as well simple console programs, Eclipse RCP fat client, simple servlets, web services and REST interfaces.</p>
              <p><a class="btn" href="https://github.com/yafraorg/yafra/wiki/Java-yafra">View details &raquo;</a></p>
            </div><!--/span-->
            <div class="span4">
              <h2>Eclipse RCP</h2>
              <p>A fat client using the Rich Client Platform of Eclipse is available as example. The fat client uses the EJB3 stubs to exchange data with the server, however you could use as well REST, Webservices or distributed OSGi.</p>
              <p><a class="btn" href="https://github.com/yafraorg/yafra/wiki/Rcpclient">View details &raquo;</a></p>
            </div><!--/span-->
            <div class="span4">
              <h2>Apache Cayenne</h2>
              <p>Apache Cayenne(tm) is an open source persistence framework licensed under the Apache License, providing object-relational mapping (ORM) and remoting services. A set of modules show how you can use your database with Cayenne and prepare for distributed transfer objects (DTO) and EJB3 usage without using the EJB3 persistence layer, which allows reuse within other setups. The example database model was created with the Cayenne Modeler application. </p>
              <p><a class="btn" href="https://github.com/yafraorg/yafra/wiki/Servercore">View details &raquo;</a></p>
            </div><!--/span-->
          </div><!--/row-->
          <div class="row">
            <div class="span4">
              <h2>Python</h2>
              <p>Python is a scripting language providing a full range of libraries easy to use within your script. If you want to do some administration or a sophisticated web application, python is an excellent choice. As python makes it easy to use C and C++ libraries, a full set of typical functions can be reused. Beside python, a couple of perl and bash scripts are available. </p>
              <p><a class="btn" href="https://github.com/yafraorg/yafra/wiki/Python">View details &raquo;</a></p>
            </div><!--/span-->
            <div class="span4">
              <h2>Continuos Integration</h2>
              <p>A simple build system which can be adapted and integrate make and ant very easy. It is based on shell script and can be scheduled via cron jobs to run on a regular basis. The system can be extended to run code analysis and create cross platform binaries if the compilers allow it. </p>
              <p><a class="btn" href="https://github.com/yafraorg/yafra/wiki/Build-system">View details &raquo;</a></p>
            </div><!--/span-->
            <div class="span4">
              <h2>Google Web Toolkit</h2>
              <p>The Google Web Toolkit (GWT) and the Google AppEngine are two technologies which allow your application to be run on Google's infrastructure. The GWT supports Java, whereas the AppEngine support Java and Python. GWT can be used within your application without using the AppEngine. An example show how it can be used with Apache Cayenne.</p>
              <p><a class="btn" href="https://github.com/yafraorg/yafra/wiki/Gwt">View details &raquo;</a></p>
            </div><!--/span-->
          </div><!--/row-->


<?php include('afooter.php');?>  
