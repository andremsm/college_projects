class Course < ApplicationRecord
    has_many :students, dependent: :destroy
    has_and_belongs_to_many :majors
end
