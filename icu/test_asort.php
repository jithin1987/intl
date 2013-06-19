<?php
$coll = collator_create("ru_RU");
$array = array( "n", "", "d", "nn" );
print_r("Input \n");
print_r($array);
$res_val = collator_asort( $coll, $array);
print_r("Output\n");
print_r($array);

$array2 = array(
  '1' => 'п',
  '4' => '',
  '7' => 'd',
  '2' => 'пп' );
print_r("Input\n");
print_r($array2);
$res_val = collator_asort( $coll, $array2);
print_r("Output\n");
print_r($array2);
?>
