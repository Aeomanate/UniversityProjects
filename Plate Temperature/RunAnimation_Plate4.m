function [] = RunAnimation_Plate4()
[X, Y, Z] = Data_Plate4();
                                                                      
minX = min(min(X(:,:)));                                              
maxX = max(max(X(:,:)));                                              
minY = min(min(Y(:,:)));                                              
maxY = max(max(Y(:,:)));                                              
minZ = min(min(min(Z(:,:,:))));                                       
maxZ = max(max(max(Z(:,:,:))));                                       
                                                                      
h = figure(1);                                                        
i = 0;                                                                
axis([minX maxX minY maxY minZ maxZ]);                                
                                                                      
isRecordGif = false;                                                  
f = getframe;                                                         
[im,map] = rgb2ind(f.cdata,256,'nodither');                           
im(1,1,1,175) = 0;                
while true                                                            
    if ~ishandle(h) % While the window with the graph is alive        
        return;                                                       
    end                                                               
                                                                      
    if i == 175                   
      if isRecordGif == true                                          
        imwrite(im,map,'Test.gif','DelayTime',t_step,'LoopCount',inf) 
        break;                                                        
      else                                                            
        i = 1;                                                        
      end                                                             
    else                                                              
        i = i + 1;                                                    
    end                                                               
                                                                      
                                                                      
    [az, el] = view; % Get current view-point                         
    surf(X, Y, Z(:,:,i));                                             
    axis([minX maxX minY maxY minZ maxZ])                             
    view([az el]);   % Set previous view-point                        
                                                                      
    grid on;                                                          
    xlabel('X');                                                      
    ylabel('Y');                                                      
    zlabel('Temperature');                                            
                                                                      
    t_step = 0.010000;                          
                                                                      
    title(['Current time: ' num2str(i * t_step)]);                    
    if isRecordGif == true                                            
        f = getframe;                                                 
        im(:,:,1,i) = rgb2ind(f.cdata,map,'nodither');                
    end                                                               
                                                                      
  % Transfer flow of execution to the functions of the interface      
    drawnow;                                                          
    pause(t_step);                                                    
end                                                                   
                                                                      
end                                                                   
