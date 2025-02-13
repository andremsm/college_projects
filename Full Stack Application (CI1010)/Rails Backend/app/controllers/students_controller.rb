class StudentsController < ApplicationController
	before_action :set_student, only: %i[ show edit update destroy ]

	# GET /students or /students.json
	def index
		@students = Student.all
		if request.fullpath.include? ".json"
#		 id = []
#		 name = []
#		 course_id = []
#		 course_name = []
#		 created_at = []
#		 updated_at = []
#		 enrolment = []
			json_full = []
			@students.each do |y|
				course_name = Course.find_by_id(y.course_id)
				json_full.push({id: y.id, name: y.name, course_id: y.course_id, course_name: course_name, created_at: y.created_at, updated_at: y.updated_at, enrolment: y.enrolment})
#	name.push(y.name)
#	course_id.push(y.course_id)
#			 course_name.push(Course.find_by_id(y.course_id))
#	created_at.push(y.created_at)
#	updated_at.push(y.updated_at)
#	enrolment.push(y.enrolment)
			end
			render json: json_full
		end
	end

	# GET /students/1 or /students/1.json
	def show
		student = Student.find_by(id: params[:id])
		course_name = Course.find_by_id(student.course_id)[:name]
		if request.fullpath.include? ".json"
			render json: {
				id: student.id,
				name: student.name,
				course_id: student.course_id,
				course_name: course_name,
				created_at: student.created_at,
				updated_at: student.updated_at,
				#url: student.url,
				enrolment: student.enrolment,
				test: "asdfasdfasdf"
			}
		end
	end

	# GET /students/new
	def new
		@student = Student.new
	end

	# GET /students/1/edit
	def edit
	end

	# POST /students or /students.json
	def create
		if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

		enrolment = Enrolment.new()
		enrolment.code = params[:student][:enrolment]

		course = Course.find_by_id(params[:student][:course_id])

		@student = Student.new()
		@student.name = params[:student][:name]
		@student.enrolment = enrolment
		@student.course = course

		respond_to do |format|
			if @student.save
				#format.html { redirect_to student_url(@student), notice: "Student was successfully created." }
				#format.json { render :show, status: :created, location: @student }
				format.json { head :no_content }
			else
				#format.html { render :new, status: :unprocessable_entity }
				#format.json { render json: @student.errors, status: :unprocessable_entity }
				format.json { head :no_content, status: :unprocessable_entity }
			end
		end
	end

	# PATCH/PUT /students/1 or /students/1.json
	def update
		if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

		#old_enrolment = @student.enrolment

		#enrolment = Enrolment.new()
		#enrolment.code = params[:student][:enrolment]

		#@student.enrolment.code = params[:student][:enrolment]

		if params[:student][:name].empty?
		else
			name = params[:student][:name]
			@student.name = name
			if @student.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end
		if params[:student][:course_id].empty?
		else
			course_id = params[:student][:course_id]
			course = Course.find_by_id(course_id.to_i)
			@student.course_id = course_id
			@student.course = course
			if @student.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end
		if params[:student][:enrolment].empty?
		else
			enrolment = @student.enrolment
			enrolment.code = params[:student][:enrolment]

			if enrolment.save
				#old_enrolment.destroy
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end
		end

		respond_to do |format|
			if true #@student.update(student_params)
				#format.html { redirect_to student_url(@student), notice: "Student was successfully updated." }
				#format.json { render :show, status: :ok, location: @student }
				format.json { head :no_content }
			else
				#format.html { render :edit, status: :unprocessable_entity }
				#format.json { render json: @student.errors, status: :unprocessable_entity }
				format.json { head :no_content, status: :unprocessable_entity }
			end
		end
	end

	def is_admin_token(token)
		user = User.find_by(login: "admin")
		admin_token = encode_user_data({ user_data: user.id })
		puts user.login
		puts admin_token
		puts token

		if token == admin_token
			return true
		else
			return false
		end
	end

	# DELETE /students/1 or /students/1.json
	def destroy
		if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

		@student.destroy

		respond_to do |format|
			#format.html { redirect_to students_url, notice: "Student was successfully destroyed." }
			format.json { head :no_content }
			#render json: {message: "ok"}
		end
	end

	private
		# Use callbacks to share common setup or constraints between actions.
		def set_student
			@student = Student.find(params[:id])
		end

		# Only allow a list of trusted parameters through.
		def student_params
			params.require(:student).permit(:name)
		end
end
