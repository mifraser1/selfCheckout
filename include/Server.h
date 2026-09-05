#pragma once

class Transaction;
class Ledger;
class MockScale;

void runServer(Transaction& tx, Ledger& ledger, MockScale& scale);