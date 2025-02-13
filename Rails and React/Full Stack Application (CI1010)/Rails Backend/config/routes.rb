Rails.application.routes.draw do
  resources :majors
  resources :courses
  resources :students
  resources :enrolments

  post "/login", to: "sessions#login"
  post "/signup", to: "sessions#signup"

  resources :todos
  
  # Define your application routes per the DSL in https://guides.rubyonrails.org/routing.html

  # Defines the root path route ("/")
  # root "articles#index"
end
