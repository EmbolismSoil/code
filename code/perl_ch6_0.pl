#!/usr/bin/perl  -w
print "enter you weight";
$_=<STDIN>;
s/^\s+//;

print $_;
if(m/(lbs|kg|kilograms|pounds?)/) ##
{
   if(s/\s*(kg|kilograms?).*//)
    {
	print $_;	
	$_*=2.2;
   	}else{
   	s/^\s(lbs|pounds?).*//;
   }
}
print "your weight on moon :",$_*=0.166667,"lbs\n"
