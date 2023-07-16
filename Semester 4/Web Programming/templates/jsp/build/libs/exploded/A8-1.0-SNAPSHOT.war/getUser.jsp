<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    session = request.getSession(false);
    String username = session != null ? (String) session.getAttribute("username") : null;
    if (username != null) {
        out.print(username);
    } else {
        response.sendRedirect("login.jsp");
    }
%>
