json.extract! course, :id, :name, :codename, :created_at, :updated_at, :majors, :students
json.url course_url(course, format: :json)
