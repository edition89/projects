<?php
$name = $_POST['name'];
$email = $_POST['email'];
$phone = $_POST['phone'];
$name = htmlspecialchars($name);
$email = htmlspecialchars($email);
$phone = htmlspecialchars($phone);
$name = urldecode($name);
$email = urldecode($email);
$phone = urldecode($phone);
$name  = trim($name);
$email = trim($email);
$phone = trim($phone);
//echo $name;
//echo "<br>";
//echo $email;
//echo "<br>";
//echo $phone;
if (mail("example@mail.ru", "Заявка с сайта", " ФИО:".$name.". E-mail: ".$email ,"From: example2@mail.ru \r\n"))
 {     echo "сообщение успешно отправлено"; 
} else { 
    echo "при отправке сообщения возникли ошибки";
}?>