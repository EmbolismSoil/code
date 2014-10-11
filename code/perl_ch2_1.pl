#!/usr/bin/perl  -w
print "please enter the tmp";
$TMP=<STDIN>;
chomp $TMP;

$TMP=5*($TMP-32)/9.0;
$TMP_FLOT=int((($TMP -(int($TMP)))*100));
$TMP=int($TMP);

print qq($TMP.$TMP_FLOT\n);
