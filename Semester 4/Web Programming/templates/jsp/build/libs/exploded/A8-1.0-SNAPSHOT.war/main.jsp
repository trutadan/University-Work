<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Home</title>
</head>
<body>
<h1 id="greeting"></h1>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script>
    $(document).ready(function () {
        $.ajax({
            url: 'getUser.jsp',
            type: 'GET',
            success: function (response) {
                if (response !== '') {
                    $('#greeting').text('Hello, ' + response + '!');
                } else {
                    window.location.href = 'login.jsp';
                }
            }
        });
    });
</script>
</body>
</html>