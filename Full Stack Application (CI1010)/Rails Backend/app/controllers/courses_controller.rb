class CoursesController < ApplicationController
	before_action :set_course, only: %i[ show edit update destroy ]

	# GET /courses or /courses.json
	def index
		@courses = Course.all
	end

	# GET /courses/1 or /courses/1.json
	def show
		course = Course.find_by(id: params[:id])
		majors = []
		course.majors.each do |y|
			majors.push(y.name)
		end
		students = []
		course.students.each do |y|
			students.push(y.name)
		end
		if request.fullpath.include? ".json"
			render json: {
				id: course.id,
				name: course.name,
				codename: course.codename,
				created_at: course.created_at,
				updated_at: course.updated_at,
				#url: course.url,
				majors: majors,
				students: students,
				test: "asdfasdfasdf"
			}
		end
	end

	# GET /courses/new
	def new
	@course = Course.new
	end

	# GET /courses/1/edit
	def edit
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

	# POST /courses or /courses.json
	def create
		if !is_admin_token(params[:course][:token])
			render json: { message: "não logado ou login inválido" }
			return
		#else
		#	render json: { message: "login aceito" }
		#	return
		end
		#return
		@course = Course.new()
		@course.name = params[:course][:name]
		@course.codename = params[:course][:codename]

		major_ids = params[:course][:major_ids]
		major_ids.each do |y|
			major = Major.find_by_id(y)
			if major
				@course.majors.push(major)
			end
		end
		
		respond_to do |format|
			if @course.save
				#format.html { redirect_to course_url(@course), notice: "Course was successfully created." }
				#format.json { render :show, status: :created, location: @course }
				format.json { head :no_content }
			else
				#format.html { render :new, status: :unprocessable_entity }
				#format.json { render json: @course.errors, status: :unprocessable_entity }
				format.json { head :no_content, status: :unprocessable_entity }
			end
		end
	end

	# PATCH/PUT /courses/1 or /courses/1.json
	def update
		#course.majors.clear
		#maybe change the permitted :major_ids param below
		if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

		if params[:course][:name].empty?
		else
			name = params[:course][:name]
			@course.name = name
			if @course.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end
		if params[:course][:codename].empty?
		else
			codename = params[:course][:codename]
			@course.codename = codename
			if @course.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end
		if (!(params[:course][:major_ids].empty?))
			@course.majors.clear

			major_ids = params[:course][:major_ids]
			major_ids.each do |y|
				major = Major.find_by_id(y)
				if major
					@course.majors.push(major)
				end
			end
			if @course.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end

		respond_to do |format|
			if true# @course.update(course_params)
				#format.html { redirect_to course_url(@course), notice: "Course was successfully updated." }
				#format.json { render :show, status: :ok, location: @course }
				format.json { head :no_content }
			else
				#format.html { render :edit, status: :unprocessable_entity }
				#format.json { render json: @course.errors, status: :unprocessable_entity }
				format.json { head :no_content, status: :unprocessable_entity }
			end
		end
	end

	# DELETE /courses/1 or /courses/1.json
	def destroy
		if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

		@course.destroy

		respond_to do |format|
			#format.html { redirect_to courses_url, notice: "Course was successfully destroyed." }
			format.json { head :no_content }
		end
	end

	private
	# Use callbacks to share common setup or constraints between actions.
	def set_course
		@course = Course.find(params[:id])
	end

	# Only allow a list of trusted parameters through.
	def course_params
		params.require(:course).permit(:name, :codename)
	end
end
