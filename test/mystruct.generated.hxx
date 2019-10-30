template <class Inspector>
typename Inspector::result_type inspect(Inspector& f, Bar::Foo& x) {
  return f("Bar::Foo"
   , x.bar
   , x.foo
   , x.mail
  );
}

void to_json(nlohmann::json& data, const Bar::Foo& t) {
  data["bar"] = field;
  data["foo"] = field;
  data["mail"] = field;
}
