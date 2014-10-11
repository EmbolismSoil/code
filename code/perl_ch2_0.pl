#!/usr/bin/perl -w
print qq(Monthly deposit amount ?);
$pmt=<STDIN>;
chomp $pmt;

print qq(ANnual Interest rate?);
$interest=<STDIN>;
chomp $interest;

print qq(Number of months to deposit?);

$mons=<STDIN>;
chomp $mons;

$total=$pmt * ((1 + $interest) ** $mons -1) / $interest;

print qq(After $mons months at $interest monthly you \n");
print qq(will have $total.\n");

