let await = [%bs.raw
  {|
    async function(promiseFunc) {
      var a = await promiseFunc();
      return a;
    }
  |}
];