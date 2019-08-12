module Styles = {
  open Css;

  global(
    "body",
    [margin(zero), fontFamily("Helvetica, Arial, sans-serif")],
  );

  global("h1, h2, h3", [fontWeight(`normal)]);

  global("img", [display(`block), maxWidth(pct(100.))]);

  global("a", [cursor(`pointer)]);
};

ReactDOMRe.renderToElementWithId(
  <Router.WithRouter>
    ...{(~currentRoute) => <App currentRoute />}
  </Router.WithRouter>,
  "root",
);