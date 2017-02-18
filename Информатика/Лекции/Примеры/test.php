<?php 

	$x1 = 1;
	$x2 = "1";

	if ($x1 !== $x2) {
		echo "Истина";
	}

	echo "<br>";
	echo __LINE__, " ", __FILE__, " ", __DIR__;
	echo "<br>";
	$array = array("A", "B", "C");
	echo "1: $array[0]";
	echo "<br>";
	var_dump($array);
	
	echo "<br>";
	echo phpversion();
	echo "<br>";
	echo 14;
	echo "<br>";
	echo 0xAF;

	$q;

	$v = 1;
	echo "<p>". ($v + $v*2) . "</p>";
	$i = 2;

	echo $i+$v+$q; // это нехорошо
?>
<p><?php echo $v . $v*2; ?></p>
<p><?php echo $v, $v*2; ?></p>

<p>
	Множество параметров: 
	<?php echo $i, $i*$i, " ", $i+$v ?>
</p>