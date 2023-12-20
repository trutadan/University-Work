require "test_helper"

class ConnectionCheckControllerTest < ActionDispatch::IntegrationTest
  test "should get check_connection" do
    get connection_check_check_connection_url
    assert_response :success
  end
end
