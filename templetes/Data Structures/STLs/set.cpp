// delete element from set while iterating 
for(auto it = nodes.begin() ; it != nodes.end() ; ){
        if(ban.count(minmax(*it,i))){
            it = nodes.erase(it); // return iterator on next element
        }
        else ++it;
}
