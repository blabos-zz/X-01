#!/usr/bin/perl

use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/../lib";

use Market::Message;
use Data::Dumper;

my $msg = Market::Message->new({
	'data' => 'clientId=blabos&operation=7'
});

print Dumper($msg), $/;