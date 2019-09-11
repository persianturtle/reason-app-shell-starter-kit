[@bs.val] [@bs.scope "performance"] external now: unit => float = "now";
[@bs.val]
external addEventListener: (string, unit => unit) => unit = "addEventListener";
[@bs.val]
external removeEventListener: (string, unit => unit) => unit =
  "removeEventListener";

module Styles = {
  open Css;

  let app =
    style([
      minHeight(vh(100.)),
      after([
        contentRule(""),
        transitions([
          Transition.shorthand(
            ~duration=450,
            ~timingFunction=cubicBesier(0.23, 1., 0.32, 1.),
            "opacity",
          ),
          Transition.shorthand(
            ~duration=0,
            ~timingFunction=cubicBesier(0.23, 1., 0.32, 1.),
            "transform",
          ),
        ]),
        position(fixed),
        top(zero),
        right(zero),
        bottom(zero),
        left(zero),
        backgroundColor(rgba(0, 0, 0, 0.33)),
        transform(translateX(pct(-100.))),
        opacity(0.),
        zIndex(1),
      ]),
      selector(
        "&.overlay",
        [
          after([
            transition(
              ~duration=450,
              ~timingFunction=cubicBesier(0.23, 1., 0.32, 1.),
              "opacity",
            ),
            transform(translateX(zero)),
            opacity(1.),
          ]),
        ],
      ),
      selector(
        "> header",
        [
          display(flexBox),
          alignItems(center),
          height(px(60)),
          backgroundColor(dodgerblue),
          color(white),
          boxShadows([
            Shadow.box(
              ~x=px(0),
              ~y=px(4),
              ~blur=px(5),
              ~spread=px(0),
              rgba(15, 74, 133, 0.14),
            ),
            Shadow.box(
              ~x=px(0),
              ~y=px(2),
              ~blur=px(9),
              ~spread=px(1),
              rgba(15, 74, 133, 0.12),
            ),
            Shadow.box(
              ~x=px(0),
              ~y=px(4),
              ~blur=px(2),
              ~spread=px(-2),
              rgba(15, 74, 133, 0.2),
            ),
          ]),
          selector(
            "> a",
            [
              display(flexBox),
              alignItems(center),
              width(px(32)),
              height(pct(100.)),
              padding2(~v=zero, ~h=px(10)),
              cursor(`pointer),
              selector("> img", [width(pct(100.)), height(pct(100.))]),
            ],
          ),
          selector(
            "> h1",
            [fontSize(px(26)), lineHeight(px(26)), marginLeft(px(10))],
          ),
        ],
      ),
      selector(
        "> nav",
        [
          transition(
            ~duration=450,
            ~timingFunction=cubicBesier(0.23, 1., 0.32, 1.),
            "transform",
          ),
          position(absolute),
          top(zero),
          left(zero),
          transform(translateX(`calc((`sub, pct(-100.), px(10))))),
          height(vh(100.)),
          backgroundColor(white),
          boxShadows([
            Shadow.box(
              ~x=px(0),
              ~y=px(3),
              ~blur=px(10),
              rgba(0, 0, 0, 0.16),
            ),
            Shadow.box(
              ~x=px(0),
              ~y=px(3),
              ~blur=px(10),
              rgba(0, 0, 0, 0.23),
            ),
          ]),
          overflow(auto),
          zIndex(2),
          selector("&.active", [transform(translateX(zero))]),
          selector(
            "> label",
            [
              fontWeight(normal),
              fontSize(px(12)),
              lineHeight(px(24)),
              textTransform(uppercase),
              display(block),
              backgroundColor(rgba(0, 0, 0, 0.32)),
              color(white),
              padding2(~v=zero, ~h=px(15)),
            ],
          ),
          selector(
            "> header",
            [
              position(relative),
              backgroundColor(lavender),
              height(px(150)),
              margin(zero),
              selector(
                "> a",
                [
                  fontSize(px(24)),
                  lineHeight(px(24)),
                  position(absolute),
                  top(zero),
                  left(zero),
                  display(flexBox),
                  alignItems(center),
                  height(px(40)),
                  padding2(~v=px(10), ~h=px(20)),
                  selector(
                    "> img",
                    [
                      width(px(20)),
                      height(px(20)),
                      marginRight(px(20)),
                    ],
                  ),
                ],
              ),
            ],
          ),
          selector(
            "> ul",
            [
              margin(zero),
              padding(zero),
              listStyleType(none),
              selector(
                "> li",
                [
                  position(relative),
                  borderBottom(px(1), solid, rgba(0, 0, 0, 0.06)),
                  after([
                    unsafe("content", "url('./img/icon/chevron.svg')"),
                    position(absolute),
                    top(zero),
                    right(px(15)),
                    bottom(zero),
                    margin(auto),
                    width(px(15)),
                    height(px(15)),
                  ]),
                  selector(
                    "> a",
                    [
                      transition(
                        ~duration=450,
                        ~timingFunction=cubicBesier(0.23, 1., 0.32, 1.),
                        "background-color",
                      ),
                      fontSize(px(18)),
                      lineHeight(px(54)),
                      textDecoration(none),
                      display(block),
                      padding2(~v=zero, ~h=px(15)),
                      color(black),
                      selector(
                        "&.active",
                        [backgroundColor(hex("e9e9e9"))],
                      ),
                    ],
                  ),
                  selector("> img", [width(px(15)), height(px(15))]),
                ],
              ),
            ],
          ),
          media("(max-width: 767px)", [width(vw(85.))]),
          media("(min-width: 768px)", [width(px(300))]),
        ],
      ),
    ]);
};

type touches = {
  first: option((float, float)),
  last: option((float, float)),
};

type state = {
  isOpen: bool,
  touches,
};

type action =
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd;

[@react.component]
let make = (~currentRoute: Router.route) => {
  let navRef = React.useRef(Js.Nullable.null);
  let width =
    switch (Js.Nullable.toOption(React.Ref.current(navRef))) {
    | None => 0.0
    | Some(nav) => ReactDOMRe.domElementToObj(nav)##clientWidth
    };
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ToggleMenu(isOpen) => {...state, isOpen}
        | TouchStart(clientX) =>
          if (state.isOpen) {
            {
              ...state,
              touches: {
                first: Some((clientX, now())),
                last: None,
              },
            };
          } else {
            state;
          }
        | TouchMove(clientX) =>
          if (state.isOpen) {
            {
              ...state,
              touches: {
                ...state.touches,
                last: Some((clientX, now())),
              },
            };
          } else {
            state;
          }
        | TouchEnd =>
          if (state.isOpen) {
            let (x, t) =
              Belt.Option.getWithDefault(state.touches.first, (0.0, 0.0));
            let (x', t') =
              Belt.Option.getWithDefault(state.touches.last, (0.0, 0.0));
            let velocity = (x' -. x) /. (t' -. t);
            let state = {
              ...state,
              touches: {
                first: None,
                last: None,
              },
            };
            if (velocity < (-0.3) || x' < width /. 2.0) {
              {...state, isOpen: false};
            } else {
              state;
            };
          } else {
            state;
          }
        },
      {
        isOpen: false,
        touches: {
          first: None,
          last: None,
        },
      },
    );

  React.useEffect(() => {
    let handler = () => dispatch(ToggleMenu(false));
    addEventListener("popstate", handler);
    Some(() => removeEventListener("popstate", handler));
  });

  <div
    className={"App " ++ Styles.app ++ (state.isOpen ? " overlay" : "")}
    onClick={_event =>
      if (state.isOpen) {
        dispatch(ToggleMenu(false));
      }
    }
    onTouchStart={event =>
      dispatch(
        TouchStart(
          ReactEvent.Touch.changedTouches(event)##item(0)##clientX,
        ),
      )
    }
    onTouchMove={event =>
      dispatch(
        TouchMove(ReactEvent.Touch.changedTouches(event)##item(0)##clientX),
      )
    }
    onTouchEnd={_event => dispatch(TouchEnd)}>
    <header>
      <a
        onClick={event => {
          ReactEvent.Mouse.stopPropagation(event);
          dispatch(ToggleMenu(true));
        }}>
        <img src=[%raw {|require("../../../src/img/icon/hamburger.svg")|}] />
      </a>
      <h1> {ReasonReact.string(currentRoute.title)} </h1>
    </header>
    <nav
      className={state.isOpen ? "active" : ""}
      onClick={event => ReactEvent.Mouse.stopPropagation(event)}
      style={
        switch (state.touches) {
        | {first: Some((x, _)), last: Some((x', _))} =>
          ReactDOMRe.Style.make(
            ~transform=
              "translateX("
              ++ Js.Float.toString(x' -. x > 0.0 ? 0.0 : x' -. x)
              ++ "0px)",
            ~transition="none",
            (),
          )
        | _ => ReactDOMRe.Style.make()
        }
      }
      ref={ReactDOMRe.Ref.domRef(navRef)}>
      <header>
        <a onClick={_event => dispatch(ToggleMenu(false))}>
          <img src=[%raw {|require("../../../src/img/icon/arrow.svg")|}] />
          {ReasonReact.string(currentRoute.title)}
        </a>
      </header>
      <label> {ReasonReact.string("home")} </label>
      <ul>
        <li>
          <Router.NavLink href="/">
            {ReasonReact.string("Home")}
          </Router.NavLink>
        </li>
      </ul>
      <label> {ReasonReact.string("pages")} </label>
      <ul>
        <li>
          <Router.NavLink href="/page1">
            {ReasonReact.string("Page1")}
          </Router.NavLink>
        </li>
        <li>
          <Router.NavLink href="/page2">
            {ReasonReact.string("Page2")}
          </Router.NavLink>
        </li>
        <li>
          <Router.NavLink href="/page3">
            {ReasonReact.string("Page3")}
          </Router.NavLink>
        </li>
      </ul>
    </nav>
    <main>
      ReactTransitionGroup.(
        <TransitionGroup>
          <CSSTransition
            key={currentRoute.title}
            _in=true
            timeout=900
            classNames="routeTransition">
            {currentRoute.component}
          </CSSTransition>
        </TransitionGroup>
      )
    </main>
  </div>;
};
