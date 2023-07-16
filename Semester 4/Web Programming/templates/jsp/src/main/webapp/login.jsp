<%@ page contentType="text/html;charset=UTF-8" %>

<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Login Forum</title>
  <script src="scripts/jquery-3.6.0.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
</head>
<body>
<div class="container text-center">
  <form action="login" method="post">
    <div class="form-group">
      <label for="username" class="form-label">Username:</label>
      <input id="username" name="username" type="text" class="form-control">
    </div>
    <div class="form-group">
      <label for="password" class="form-label">Password:</label>
      <input id="password" name="password" type="password" class="form-control">
    </div>
    <%
      String error = (String) session.getAttribute("error");
      if (error != null) {
        out.println("<p class=\"alert alert-danger\">" + error + "</p>");
      }
    %>
    <div class="form-group">
      <button type="submit" class="btn btn-primary">Login</button>
    </div>
  </form>
</div>
</body>
</html>
