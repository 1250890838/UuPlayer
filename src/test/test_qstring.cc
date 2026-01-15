#include "test_qstring.h"

void TestQString::toUpper() {
  QString str = "Hello";
  QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(TestQString)
