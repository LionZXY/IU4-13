<!DOCTYPE html>
<html>
<head>
	<title>Форма</title>
	<meta charset="utf-8">
</head>
<body>
<form action="form.php" method="post">
	<label>Логин</label>
	<input type="text" name="name">
	<label>Пароль</label>
	<input type="password" name="pass">
	<input type="submit" value="Войти">
</form>
<?php 
	echo "Логин:" . $_POST['name'];
	echo "Пароль:" . $_POST['pass'];
?>
</body>
</html>