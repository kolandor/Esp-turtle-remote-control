os.loadAPI("tur")

local function getCommand()
  http.request("http://192.168.0.176")

  local req = true
  
  local respText = ""
  
  while req do
    local event, url, source = os.pullEvent()
    
    if event == "http_success" then
      respText = source.readAll()
      
      source.close()
      
      req = false

    elseif event == "http_failure" then
      print("Server error")
      
      req = false
    end
  end
  
  return respText
end

while true do
  cmd = getCommand()
  
  if cmd == "UP" then
    tur.forw()
  elseif cmd == "DOWN" then
    tur.back()
  elseif cmd == "LEFT" then
    tur.tLeft()
  elseif cmd == "RIGHT" then
    tur.tRight()
  end
  
  if cmd ~= "NONE" then
    os.sleep(0.5)
  end
end
