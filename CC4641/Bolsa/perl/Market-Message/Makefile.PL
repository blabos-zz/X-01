use inc::Module::Install;

name     'Market-Message';
all_from 'lib/Market/Message.pm';
author   q{Blabos de Blebe <blabos@cpan.org>};
license  'perl';

build_requires 'Test::More';

auto_install;

WriteAll;

