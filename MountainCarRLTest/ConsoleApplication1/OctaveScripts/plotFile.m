function result = plotFile( filename )
    data = dlmread(filename, ' ', 0, 0 );
    tx = unique(data(:,1));
    ty = unique(data(:,2));
    tz = reshape(-data(:,3),80,81);
    mesh(tx,ty,tz);