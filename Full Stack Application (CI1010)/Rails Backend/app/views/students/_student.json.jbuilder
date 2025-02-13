json.extract! student, :id, :name, :course_id, :created_at, :updated_at, :enrolment, :course_name
json.url student_url(student, format: :json)
