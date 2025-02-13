class CreateJoinTableMajorCourse < ActiveRecord::Migration[7.0]
  def change
    create_join_table :majors, :courses do |t|
      # t.index [:major_id, :course_id]
      # t.index [:course_id, :major_id]
    end
  end
end
