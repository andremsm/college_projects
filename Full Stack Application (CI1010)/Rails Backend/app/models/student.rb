class Student < ApplicationRecord
  belongs_to :course
  has_one :enrolment, dependent: :destroy
end
