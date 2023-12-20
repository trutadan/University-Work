class ConnectionCheckController < ApplicationController
  def check_connection
    render json: { message: "Connection successful." }, status: :ok
  end
end
