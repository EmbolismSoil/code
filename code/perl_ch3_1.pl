#!/usr/bin/perl  -w

@words=qw(internet answers printer program);

$word=$words[rand @words];

@letter=split(//,$word);
$worng=0;

$pic="O-|---<";
@man=split(//,$pic);
@manbuf=(' ') x scalar(@man);
@blank=('-') x scalar(@man);


while($worng < @letter)
{   
    $count = 0;
    
    print "@blank \n";
    print "@manbuf ";	
    $guess=<STDIN>;chomp $guess;  
     foreach $i (@letter)
     {       
        if($i eq $guess)
        {
           $blank[$count]=$guess;
	   $manbuf[$count]=$man[$count];	   
        }
       $count++;
     }
     
     $worng++ if($count > 6);	  
           
}

exit 0;
