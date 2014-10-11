#!/usr/bin/perl  -w

$max=20;


for($count = 1;$count < $max; $count += 2)
{
    for($count1 = 2; $count1 < $count; $count1++)
    {
      last if(!($count % $count1));
      print "$count\n"  if ($count1 == $count - 1);
    }
    
}
exit 0;	

	
