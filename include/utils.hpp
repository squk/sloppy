#pragma once

inline bool file_exists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

inline std::string replace_ext(std::string s, const std::string& newExt) {
    std::string::size_type i = s.rfind('.', s.length());

   if (i != std::string::npos) {
      s.replace(i+1, newExt.length(), newExt);
   }
   return s;
}
