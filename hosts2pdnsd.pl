#!/usr/bin/env perl

eval 'exec /usr/bin/perl -S $0 ${1+"$@"}'
    if 0; # not running under some shell

use strict;
use warnings;
use feature 'say';
use Data::Dump qw(dump);

my $resovle_to = '127.0.0.1';
my $depth = 2;
my %uniq;

#my @parts = (1,2,3);
#print join('.', @parts[0..$depth - 1]);
#exit;

while (<>) {
   chomp;
   my ($host, $full_domain) = split/\s/;
   #my ($tld, $domain, @subs) = reverse split/\./, $full_domain;
   my @parts = split/\./, $full_domain;
   $uniq{@parts[0..1]} = 1;

   #%uniq{"$domain.$tld"}

   #print $full_domain, "=", join(',', reverse @subs), ".$domain.$tld", "\n";
}
