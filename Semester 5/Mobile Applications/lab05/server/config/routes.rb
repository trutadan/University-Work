Rails.application.routes.draw do
  mount ActionCable.server => '/cable'
  get 'check_connection', to: 'connection_check#check_connection'
  resources :exercises
end
