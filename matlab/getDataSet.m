function dataset = getDataSet(test, full_or_half)
    if test
      switch full_or_half
      case 'fullsize'
        dataset = {{'Bowling1', 290}, {'Cloth2', 260}};
        return
      case 'halfsize'
        dataset = {{'Bowling1', 145}, {'Cloth2', 130}};
        return
      end
    end


% not test
  switch full_or_half
  case 'fullsize'
    dataset = {{'Aloe', 270}, {'Baby1', 300}, {'Baby2', 300}, ...
        {'Baby3', 250}, {'Bowling1', 290}, {'Bowling2', 240},...
        {'Cloth1', 290}, ...
        {'Cloth2', 260}, ...
        {'Cloth3', 290}, ...
        {'Cloth4', 260}, ...
        {'Flowerpots', 251}, ...
        {'Lampshade1', 260}, ...
        {'Lampshade2', 260}, ...
        {'Midd1', 196}, ...
        {'Midd2', 214}, ...
        {'Monopoly', 237}, ...
        {'Plastic', 280}, ...
        {'Rocks1', 274}, ...
        {'Rocks2', 274}, ...
        {'Wood1', 210}, ...
        {'Wood2', 254}, ...
        }; 
    return

  case 'halfsize'
    dataset = {
      {'Aloe', 135}, ...
      {'Baby1', 150}, ...
      {'Baby2', 150}, ...
      {'Baby3', 125}, ...
      {'Bowling1', 145}, ...
      {'Bowling2', 120}, ...
      {'Cloth1', 145}, ...
      {'Cloth2', 130}, ...
      {'Cloth3', 145}, ...
      {'Cloth4', 130}, ...
      {'Cones', 118}, ...
      {'Flowerpots', 125}, ...
      {'Lampshade1', 130}, ...
      {'Lampshade2', 130}, ...
      {'Midd1', 98}, ...
      {'Midd2', 107}, ...
      {'Monopoly', 118}, ...
      {'Plastic', 140}, ...
      {'Rocks1', 137}, ...
      {'Rocks2', 137}, ...
      {'Teddy', 118}, ...
      {'Wood1', 105}, ...
      {'Wood2', 127}, ...
    };
  end
end