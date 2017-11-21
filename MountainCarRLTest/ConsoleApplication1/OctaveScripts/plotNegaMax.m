function result = plotNegaMax( valActOneFile, valActTwoFile, valActThreeFile )
    data1 = dlmread(valActOneFile, ' ', 0, 0 );
    data2 = dlmread(valActTwoFile, ' ', 0, 0 );
    data3 = dlmread(valActThreeFile, ' ', 0, 0 );
    
    data = data1;
    data(:,3) = max( max(data1(:,3),data2(:,3) ), data3(:,3) );
    tx = unique(data(:,1));
    ty = unique(data(:,2));
    tz = reshape(-data(:,3),80,81);
    mesh(tx,ty,tz);