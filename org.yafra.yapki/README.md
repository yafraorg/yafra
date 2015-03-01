# YAPKI - Yet another PKI system

Build on top of openssl this directoy holds a simple homebrew PKI for you.

It contains a guide, some scripts and configs in order to run a PKI mainly on UNIX boxes.

## Install

* Run CA.pl -newca (for the CA cert a common name is recommended like CA-Admin)
* Publish the new CA public certificate
* Run genwwwcert.sh to generate a Web Server certificate like for apache or nginx
* Generate you cert request through a web interface
* Sign the generated cert requests by the CA
* Run gensshcert.sh to generate a SSH certificate like for Putty or openssh
* Run gencrl.sh to generate a CRL lits to be published
