class Major < ApplicationRecord
    has_and_belongs_to_many :courses
end
