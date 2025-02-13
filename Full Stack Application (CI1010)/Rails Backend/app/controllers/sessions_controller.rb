class SessionsController < ApplicationController
	def signup
		user_exists = User.find_by_login(params[:login])
		if user_exists
			render json: { message: "login não permitido" }
			return
		end
		user = User.new(login: params[:login], password: params[:password])
	
		# if user is saved
		if user.save
			# we encrypt user info using the pre-define methods in application controller
			token = encode_user_data({ user_data: user.id })
	
			# return to user
			render json: { token: token }
		else
			# render error message
			render json: { message: "credenciais inválidas" }
		end
	end

	def login
		user = User.find_by_login(params[:login])
		
		# you can use bcrypt to password authentication
		if user && user.password == params[:password]
	
			# we encrypt user info using the pre-define methods in application controller
			token = encode_user_data({ user_data: user.id })
			puts token
			# return to user
			if user.login == "admin"
				render json: { token: token, admin: true }
			else
				render json: { token: token, admin: false }
			end
		else
			render json: { message: "credenciais inválidas" }, status: :unauthorized
		end
	end
	end