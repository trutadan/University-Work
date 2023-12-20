class ExercisesController < ApplicationController
    before_action :set_exercise, only: [:update, :destroy]

    def index
        @exercises = Exercise.all
        render json: @exercises.as_json(except: [:created_at, :updated_at]), status: :ok
    end

    def create
        @exercise = Exercise.new(exercise_params)

        if @exercise.save
            broadcast_change("create", @exercise.as_json(except: [:created_at, :updated_at]))
            render json: @exercise.as_json(except: [:created_at, :updated_at]), status: :created
        else
            render json: @exercise.errors, status: :unprocessable_entity
        end
    end
    
    def update
        if @exercise.update(exercise_params)
            broadcast_change("update", @exercise.as_json(except: [:created_at, :updated_at]))
            render json: @exercise.as_json(except: [:created_at, :updated_at]), status: :ok
        else
            render json: @exercise.errors, status: :unprocessable_entity
        end
    end
    
    def destroy
        @exercise.destroy

        broadcast_change("delete", { id: params[:id] })
        render json: "Exercise deleted.", status: :ok
    end

    private
        def set_exercise
            @exercise = Exercise.find(params[:id])
        end

        def exercise_params
            params.require(:exercise).permit(:name, :description, :category, :primary_muscle, :secondary_muscles, :equipment, :image)
        end

        def broadcast_change(type, payload)
            ActionCable.server.broadcast("exercise_channel", { type: type, payload: payload })
        end
  end
  