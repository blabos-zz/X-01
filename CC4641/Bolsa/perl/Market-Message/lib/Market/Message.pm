package Market::Message;

use warnings;
use strict;

=head1 NAME

Market::Message - The great new Market::Message!

=head1 VERSION

Version 0.01

=cut

our $VERSION = '0.01';


=head1 SYNOPSIS

Quick summary of what the module does.

Perhaps a little code snippet.

    use Market::Message;

    my $foo = Market::Message->new();
    ...

=head1 EXPORT

A list of functions that can be exported.  You can delete this section
if you don't export anything, such as for a purely object-oriented module.

=head1 SUBROUTINES/METHODS

=head2 new

=cut

sub new {
    my $class   = shift;
    my $args    = shift || {};
    my $atts    = {
        'data' => $args->{'data'} || '',
    };
    
    from_str($atts, $atts->{'data'}) if $atts->{'data'};
    
    return bless($atts, $class);
}

=head2 from_str

=cut

sub from_str {
    my $self = shift;
	my $data = shift;
    my @params = split '&', $data;
    
	foreach my $param (@params) {
        my @pair = split '=', $param;
        $self->{'fields'}->{$pair[0]} = $pair[1];
	}
}

=head2 to_str

=cut

sub to_str {
    my $self = shift;
    my %fields = %{$self->{'fields'}};
    
    $self->{'data'} = '';
    foreach my $key (keys %fields) {
        $self->{'data'} .= $key . '=' . $fields{$key} . '&';
    }
    
    return $self->{'data'};
}

=head1 AUTHOR

Blabos de Blebe, C<< <blabos at cpan.org> >>

=head1 BUGS

Please report any bugs or feature requests to C<bug-market-message at rt.cpan.org>, or through
the web interface at L<http://rt.cpan.org/NoAuth/ReportBug.html?Queue=Market-Message>.  I will be notified, and then you'll
automatically be notified of progress on your bug as I make changes.




=head1 SUPPORT

You can find documentation for this module with the perldoc command.

    perldoc Market::Message


You can also look for information at:

=over 4

=item * RT: CPAN's request tracker

L<http://rt.cpan.org/NoAuth/Bugs.html?Dist=Market-Message>

=item * AnnoCPAN: Annotated CPAN documentation

L<http://annocpan.org/dist/Market-Message>

=item * CPAN Ratings

L<http://cpanratings.perl.org/d/Market-Message>

=item * Search CPAN

L<http://search.cpan.org/dist/Market-Message/>

=back


=head1 ACKNOWLEDGEMENTS


=head1 LICENSE AND COPYRIGHT

Copyright 2010 Blabos de Blebe.

This program is free software; you can redistribute it and/or modify it
under the terms of either: the GNU General Public License as published
by the Free Software Foundation; or the Artistic License.

See http://dev.perl.org/licenses/ for more information.


=cut

1; # End of Market::Message
