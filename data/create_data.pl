use 5.24.1;

my $product;
my @list='a'..'z';

say 1;
say "1000,200,300,400,900,600,700,600,300";

for (1..100){
	$product="";
	$product.=$list[rand(26)] for(0..5);
	say $_.",".int(rand(12)+1).",".int(rand(30)+1).",".int(rand(3000)+10).",".int(rand(51)).",".$product;
}
