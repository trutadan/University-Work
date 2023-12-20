class CreateExercises < ActiveRecord::Migration[7.1]
  def change
    create_table :exercises do |t|
      t.string :name
      t.string :description
      t.string :category
      t.string :primary_muscle
      t.string :secondary_muscles
      t.string :equipment
      t.string :image

      t.timestamps
    end
  end
end
