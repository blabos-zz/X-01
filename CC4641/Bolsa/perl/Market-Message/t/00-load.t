#!perl -T

use Test::More tests => 1;

BEGIN {
    use_ok( 'Market::Message' ) || print "Bail out!
";
}

diag( "Testing Market::Message $Market::Message::VERSION, Perl $], $^X" );
