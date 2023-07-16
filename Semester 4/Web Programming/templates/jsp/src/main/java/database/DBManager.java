package database;

import domain.User;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBManager {
    private static final String DATABASE = "jdbc:postgresql://localhost:5432/jsp_template";
    private static final String USERNAME = "postgres";
    private static final String PASSWORD = "admin";

    public DBManager() {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public User getUserWithUsername(String username) {
        User user = null;
        String statement = "SELECT * FROM users U WHERE U.username = ?";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setString(1, username);
            var rs = preparedStatement.executeQuery();
            if (rs.next()) {
                user = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }

        return user;
    }

    public User authenticate(String username, String password) {
        User user = getUserWithUsername(username);
        if (user != null && user.getPassword().equals(password)) {
            return user;
        }
        return null;
    }

    public User getUserWithId(int userId) {
        User user = null;
        String statement = "SEELCT * FROM users U WHERE U.id = ?";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, userId);
            var rs = preparedStatement.executeQuery();
            if (rs.next()) {
                user = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }

        return user;
    }
}
