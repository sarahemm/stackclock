#!/usr/bin/perl -w

# turn a text file of which segments to turn on for each character into a C array
# intended to turn 16-segment font descriptions into C files
# also used for generating 7-segment font definitions w/ slight modification after generation

use strict;

my %bit_pos;
my @chars;
while(<>) {
  next if !/(\S+)\s*=\s*(.+)/;
  my $key = $1;
  my $segs_on = $2;
  if($key eq "bitorder") {
    my $bit_def = $segs_on;
    $bit_def =~ s/\s//g;
    for(my $bit_pos = 0; $bit_pos < length($bit_def); $bit_pos++) {
      my $bit_key = substr($bit_def, $bit_pos, 1);
      $bit_pos{$bit_key} = $bit_pos;
    }
  } else {
    my $char_def = 0;
    foreach my $bit (split(//, $segs_on)) {
      $char_def = $char_def | (1<<$bit_pos{$bit});
    }
    $chars[ord($key)] = $char_def;
  }
}

#print("\nGenerated using fonttxt2array.pl\nstatic const unsigned short alpha_font[] PROGMEM = {\n\t");
print("\n// Generated using fonttxt2array.pl\nstatic const unsigned short alpha_font[] = {\n\t");
for(my $char_nbr = 0; $char_nbr < 127; $char_nbr++) {
  $chars[$char_nbr] = 0 if !defined $chars[$char_nbr];
  if($char_nbr < 127) {
    printf "0x%04X, ", $chars[$char_nbr];
  } else {
    printf "0x%04X", $chars[$char_nbr];
  }
  if(($char_nbr + 1) % 5 == 0) {
    print("\n\t");
  }
}
print "\n};\n\n";