class ApplicationController < ActionController::Base
    protect_from_forgery with: :exception, if: Proc.new { |c| c.request.format != 'application/json' }
    protect_from_forgery with: :null_session, if: Proc.new { |c| c.request.format == 'application/json' }

    SECRET = "yoursecretword"

    def authentication
        # making a request to a secure route, token must be included in the headers
        decode_data = decode_user_data(request.headers["token"])
        # getting user id from a nested JSON in an array.
        user_data = decode_data[0]["user_id"] unless !decode_data
        # find a user in the database to be sure token is for a real user
        user = User.find(user_data&.id)

        # The barebone of this is to return true or false, as a middleware
        # its main purpose is to grant access or return an error to the user

        if user
        return true
        else
        render json: { message: "invalid credentials" }
        end
    end

    # turn user data (payload) to an encrypted string  [ A ]
    def encode_user_data(payload)
        token = JWT.encode payload, SECRET, "HS256"
        return token
    end

    # turn user data (payload) to an encrypted string  [ B ]
    def encode_user_data(payload)
        JWT.encode payload, SECRET, "HS256"
    end

    # decode token and return user info, this returns an array, [payload and algorithms] [ A ]
    def decode_user_data(token)
        begin
        data = JWT.decode token, SECRET, true, { algorithm: "HS256" }
        return data
        rescue => e
        puts e
        end
    end

    # decode token and return user info, this returns an array, [payload and algorithms] [ B ]
    def decode_user_data(token)
        begin
        JWT.decode token, SECRET, true, { algorithm: "HS256" }
        rescue => e
        puts e
        end
    end

    class TodosController < ApplicationController

        # authentication is the method we define in application_controller.rb to check request.headers['token']
        
          before_action :authentication
        
          # GET /todos
          def index
            @todos = Todo.all
        
            render json: @todos
          end
        end
end
