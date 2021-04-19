<?php
$name = $_POST['name'];
$email = $_POST['email'];
$tel = $_POST['tel'];
$name = htmlspecialchars($name);
$email = htmlspecialchars($email);
$tel = htmlspecialchars($tel);
$name = urldecode($name);
$email = urldecode($email);
$tel = urldecode($tel);
$name = trim($name);
$email = trim($email);
$tel = trim($tel);
if (mail("roman_gabibullae@mail.ru", "Заявка с сайта", "ФИО:".$name.". E-mail: ".$email. " Телефон:".$tel ,"From: lol@mail.ru \r\n"))
 {     echo "сообщение успешно отправлено";
} else {
    echo "при отправке сообщения возникли ошибки";
}?>
