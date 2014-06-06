use strict;
use warnings;

use admin;

my $app = admin->apply_default_middlewares(admin->psgi_app);
$app;

