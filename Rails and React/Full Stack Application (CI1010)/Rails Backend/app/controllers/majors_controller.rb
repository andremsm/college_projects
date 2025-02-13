class MajorsController < ApplicationController
  before_action :set_major, only: %i[ show edit update destroy ]

  # GET /majors or /majors.json
  def index
    @majors = Major.all
  end

  # GET /majors/1 or /majors/1.json
  def show
	'''if request.fullpath.include? ".json"
		puts "====================="
		puts request.fullpath
		puts "====================="
	end'''
    major = Major.find_by(id: params[:id])
    #courses = []
    #puts "parametros: " + params.to_s
    #major.courses.each do |y|
		#puts y.name
    #    courses.push(y.name)
    #end
	if request.fullpath.include? ".json"
		render json: {
			id: major.id,
			name: major.name,
			created_at: major.created_at,
			updated_at: major.updated_at,
			#url: major.url,
			courses: major.courses,
			test: "asdfasdfasdf"
		}
	end
  end

  # GET /majors/new
  def new
    @major = Major.new
  end

  # GET /majors/1/edit
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

  # POST /majors or /majors.json
  def create
    if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end
	'''
	course_ids = params[:major][:course_ids]
	puts course_ids.class
	params[:major][:course_ids].each do |y|
		puts y
	end
	puts "parametros: " + params[:major][:course_ids].to_s
	return
	'''
    @major = Major.new(major_params)
	course_ids = params[:major][:course_ids]
	course_ids.each do |y|
		course = Course.find_by_id(y)
		if course
			@major.courses.push(course)
		end
	end

    respond_to do |format|
      if @major.save
        format.html { redirect_to major_url(@major), notice: "Major was successfully created." }
        format.json { render :show, status: :created, location: @major }
      else
        format.html { render :new, status: :unprocessable_entity }
        format.json { render json: @major.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /majors/1 or /majors/1.json
  def update
    	if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

		if params[:major][:name].empty?
		else
			name = params[:major][:name]
			@major.name = name
			if @major.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end
		if (!(params[:major][:course_ids].empty?))
			@major.courses.clear

			course_ids = params[:major][:course_ids]
			course_ids.each do |y|
				course = Course.find_by_id(y)
				if course
					@major.courses.push(course)
				end
			end
			if @major.save
			else
				format.json { head :no_content, status: :unprocessable_entity }
			end	
		end
		#puts major_params

    respond_to do |format|
      if true #@major.update(major_params)
        #format.html { redirect_to major_url(@major), notice: "Major was successfully updated." }
        #format.json { render :show, status: :ok, location: @major }
		format.json { head :no_content }
      else
        #format.html { render :edit, status: :unprocessable_entity }
        #format.json { render json: @major.errors, status: :unprocessable_entity }
		format.json { head :no_content, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /majors/1 or /majors/1.json
  def destroy
    if (!is_admin_token(params[:token]))
			render json: { message: "não logado ou login inválido" }
			return
		end

    @major.destroy

    respond_to do |format|
      #format.html { redirect_to majors_url, notice: "Major was successfully destroyed." }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_major
      @major = Major.find(params[:id])
    end

    # Only allow a list of trusted parameters through.
    def major_params
      params.require(:major).permit(:name)
    end
end
