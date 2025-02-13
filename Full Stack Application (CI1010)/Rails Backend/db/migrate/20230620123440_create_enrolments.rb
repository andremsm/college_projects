class CreateEnrolments < ActiveRecord::Migration[7.0]
  def change
    create_table :enrolments do |t|
      t.string :code
      t.belongs_to :student, null: false, foreign_key: true

      t.timestamps
    end
  end
end
