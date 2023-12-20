class Exercise < ApplicationRecord
    validates :name, presence: { message: 'cannot be blank or contain only whitespace' }
    validates :description, presence: { message: 'cannot be blank or contain only whitespace' }
    validates :category, presence: { message: 'cannot be blank or contain only whitespace' }
    validates :primary_muscle, presence: { message: 'cannot be blank or contain only whitespace' }
    validates :secondary_muscles, presence: { message: 'cannot be blank or contain only whitespace' }
    validates :equipment, presence: { message: 'cannot be blank or contain only whitespace' }
end
