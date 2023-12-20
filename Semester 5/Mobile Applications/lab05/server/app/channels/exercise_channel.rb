class ExerciseChannel < ApplicationCable::Channel
  def subscribed
    stream_from "exercise_channel"
  end

  def unsubscribed
  end

  def receive(data)
  end
end
