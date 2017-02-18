<!DOCTYPE html>
<html>
<head>
	<title>Validation</title>
	<meta charset="utf-8">
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<?php
	$error = "";
	if (empty($_POST["name"])) {
		$error = "Ошибка";
	}
?>
<form method="post" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">
	<input type="text" name="name" value="<?php echo $_POST['name']; ?>">
	<span class="error"><?php echo $error; ?></span>
	<input type="submit" name="Отправить">
</form>
<?php 
	echo htmlspecialchars($_POST["name"]);
?>
</body>
</html>